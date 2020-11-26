def main():
    i = get_positive_int()
    print(i)

def get_positive_int():
    while True:
        n = int(input("Positive integer: "))    # input return str
        if n > 0:
            break
    return n                # variables are available out of declared scope,
                            # but not across functions, except global
main()
