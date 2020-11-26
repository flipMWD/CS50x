import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Implement:
# register, quote (stock value), buy, index (user stocks), sell, history
# Personal Touch: change password, add cash, password requirements, etc

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# API_KEY=pk_f5c38be3b3db49e4bf2e5d2794be0d58
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                           user_id=session["user_id"])

    if not user_cash:
        return apology("could not find user information", 403)

    # select symbol, sum (share op buy - share op sell)
    user_stocks = db.execute("SELECT symbol, shares \
                              FROM stocks \
                              WHERE user_id = :user_id \
                              ORDER BY symbol ASC", user_id=session["user_id"])

    if not user_stocks:
        return apology("user does not have stocks", 409)

    cur_values = list()
    shares_value = 0
    for i, row in enumerate(user_stocks):
        cur_values.append((lookup(row["symbol"]), row["shares"]))
        shares_value += cur_values[i][0]["price"] * cur_values[i][1]

    return render_template("index.html", table_rows=cur_values,
                           total_cash=usd(user_cash[0]["cash"]),
                           grand_total=usd(user_cash[0]["cash"] + shares_value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("symbol field empty", 403)
        else:
            symbol = symbol.upper()

        quote_info = lookup(symbol)
        user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                               user_id=session["user_id"])

        shares = request.form.get("shares")
        if not shares:
            return render_template("buyinfo.html", symbol=symbol,
                                   quote_info=quote_info,
                                   total_cash=usd(user_cash[0]["cash"]))
        else:
            shares = int(shares)

        if shares < 1:
            return apology("shares field must have a positive number", 403)

        total_price = shares * quote_info["price"]
        if total_price > user_cash[0]["cash"]:
            return apology("insuficient cash", 409)

        # Write to history
        db.execute("INSERT INTO historyStocks \
                    (user_id, operation, symbol, price, shares, date) \
                    VALUES (?, 'buy', ?, ?, ?, ?)",
                   session["user_id"], symbol, quote_info["price"], shares,
                   datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

        # Write to stocks
        entry_updated = db.execute("UPDATE stocks \
                                    SET shares = shares + :shares \
                                    WHERE user_id = :user_id \
                                    AND symbol = :symbol",
                                   shares=shares,
                                   user_id=session["user_id"],
                                   symbol=symbol)
        if not entry_updated:
            db.execute("INSERT INTO stocks (user_id, symbol, shares) \
                        VALUES (?, ?, ?)", session["user_id"], symbol, shares)

        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                   cash=(user_cash[0]["cash"] - total_price),
                   user_id=session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # GROUP BY substr(date, 1, 12) \
    user_history = db.execute("SELECT operation, symbol, price, shares, date \
                               FROM historyStocks \
                               WHERE user_id = :user_id \
                               ORDER BY date DESC", user_id=session["user_id"])

    return render_template("history.html", table_rows=user_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("symbol field empty", 403)

        quote_info = lookup(request.form.get("symbol"))

        return render_template("quoted.html", quote_info=quote_info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("confirmation"):
            return apology

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        if len(rows) >= 1:
            return apology("username already exists", 409)

        password = request.form.get("password")
        if password != request.form.get("confirmation"):
            return apology("password does not match", 409)

        if len(password) < 4:
            return apology("password must have more than 4 characters", 409)

        hash_password = generate_password_hash(password)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), hash_password)

        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("no symbol selected", 403)

        quote_info = lookup(symbol)

        shares = request.form.get("shares")
        if not shares:
            return apology("shares field must have a value", 403)
        else:
            shares = int(shares)

        if shares < 1:
            return apology("shares field must have a positive number", 403)

        entry_updated = db.execute("UPDATE stocks SET shares = shares - :shares \
                                    WHERE user_id = :user_id \
                                    AND symbol = :symbol \
                                    AND shares > :shares",
                                    user_id=session["user_id"],
                                    symbol=symbol, shares=shares)
        if not entry_updated:
            entry_deleted = db.execute("DELETE FROM stocks \
                                        WHERE user_id = :user_id \
                                        AND symbol = :symbol \
                                        AND shares = :shares",
                                       user_id=session["user_id"],
                                       symbol=symbol, shares=shares)
            if not entry_deleted:
                return apology("not enough shares to sell", 409)

        if entry_updated or entry_deleted:
            db.execute("INSERT INTO historyStocks \
                        (user_id, operation, symbol, price, shares, date) \
                        VALUES (?, 'sell', ?, ?, ?, ?)",
                       session["user_id"], symbol, quote_info["price"], shares,
                       datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

            db.execute("UPDATE users SET cash = cash + :cash WHERE id = :user_id",
                       cash=(shares * quote_info["price"]),
                       user_id=session["user_id"])

        return redirect("/")

    else:
        user_stocks = db.execute("SELECT symbol FROM stocks \
                                  WHERE user_id = :user_id",
                                 user_id=session["user_id"])
        if not user_stocks:
            return apology("user does not have stocks", 409)

        return render_template("sell.html", quote_info=user_stocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
