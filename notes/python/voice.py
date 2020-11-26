import speech_recognition

words = input("Say somehting!\n").lower()

if "hello" in words:
    print("Hello to you too!")
elif "how are you" in words:
    print("I'm well, thanks!")
elif "goodbye" in words:
    print("Goodbye to you too!")
else:
    print("Huh?")

#-----------------

recognizer = speech_recognition.Recognizer()
with speech_recognition.Microphone() as source:
    print("Say something!")
    audio = recognizer.listen(source)

print("Google Speech Recognition thinks you said:")
print(recognizer.recognize_google(audio))
