# pacman -S python-qrcode
import qrcode

image = qrcode.make("https://youtu.be/fL308_-Kbt0?t=6422")
image.save("qr.png", "PNG")
