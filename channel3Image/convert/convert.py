#!/bin/env python3

from PIL import Image, ImageOps, ImageDraw

IMAGE_FILE = "image.png"
OUTSCRIPT = "data.h"

def _ResizeImage(image):
	"""Resizes the passed image to fit on the label.
	Returns resized image object"""

	if(isinstance(image, str)):
		img = Image.open(image)
	elif(isinstance(image, Image.Image)):
		img = image
	else:
		raise ValueError("image parameter is neither a string nor an Image object!")

	maxWidth = 232
	maxHeight = 264

	imgWidth = img.size[0]
	imgHeight = img.size[1]
	
	# resize the image
	newHeight = int( (maxWidth / imgWidth) * imgHeight)
	if(newHeight > maxHeight):
		newHeight = maxHeight
		#raise ValueError("Image \""+image+"\" is too tall!")
	newImg = img.resize((maxWidth, newHeight))

	return newImg

def _ConvertImageTo1bppx(img, threshold):
	"""Converts the image object "img" to a 1bppx array.
	Returns this array as well as the size of the image"""

	bgImage = Image.new("RGBA", img.size, color=255)
	bgImage.paste(img)

	# Convert image to greyscale
	greyImg = bgImage.convert("L", dither=None)
	# B&W image is inverted
	bwImg = greyImg.point((lambda p: p<threshold),mode="1")

	# Get array with pixel data(array with the 3 rgb values)
	pixels = list(bwImg.getdata())
	
	imgWidth = img.size[0]
	imgHeight = img.size[1]

	return pixels, imgWidth, imgHeight

img = _ResizeImage(IMAGE_FILE)

(pixels, w, h) = _ConvertImageTo1bppx(img, 64)

with open(OUTSCRIPT, "w") as f:
    f.write("#ifndef DATA_H\n#define DATA_H\n")
    f.write("// Generated header file from image\n")
    f.write("#include<Arduino.h>\n")

    f.write(f"#define DATA_WIDTH {w}\n")
    f.write(f"#define DATA_HEIGHT {h}\n")

    f.write("const uint8_t dataArray[] PROGMEM = {\n")    

    for i in range(h):
        f.write("\t")        
        for j in range(w):
            f.write(f"{pixels[j+i*w]}, ")
        f.write("\n")        

    f.write("};\n")

    f.write("#endif\n")


