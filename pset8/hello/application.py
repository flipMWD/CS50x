import random
from flask import Flask, render_template, request


app = Flask(__name__)

# When you go to this default / route, call index function
@app.route("/")
def index():
    python_number = random.randint(1, 10)
    p_coin_flip = random.randint(0, 1)
    return render_template("index.html",
                           name="Emma",
                           template_number=python_number,
                           t_coin_flip=p_coin_flip)

@app.route("/hello")
def hello():
    name = request.args.get("name")
    if not name:
        return render_template("failure.html")
    return render_template("hello.html", name=name)

@app.route("/goodbye")
def bye():
    return "Goodbye!"