words = set()

def check(word):
    if word.lower() in words:               # str class has method lower
        return True
    else:
        return False

def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n"))        # add method from set class
    file.close()                            # reverse strip, end to beginning
    return True

def size():
    return len(words)

def unlaod():
    return True                             # python has garbage collection
