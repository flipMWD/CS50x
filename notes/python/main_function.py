def main():
    cough(5)
    print(example('AMD FX-4100'))

def cough(n):
    for i in range(n):
        print("cough")

# Annotations are expressions after : and -> to give optional metadata
# information about the types used by functions
def example(cpu: str, gpu: str = "Ati Radeon HD6970") -> str:
    return cpu + " and " + gpu

main()
