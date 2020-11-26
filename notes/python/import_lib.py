# pacman -S python-pillow
from PIL import Image, ImageFilter

before = Image.open("images/courtyard.bmp")
after = before.filter(ImageFilter.BLUR)
after.save("blur_courtyard.bmp")
