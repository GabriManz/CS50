import sys
import random
from pyfiglet import Figlet

# Initialize figlet
figlet = Figlet()

# Store number of arguments
argc = len(sys.argv)

# Get list of fonts and initialize figlet with a random one
fonts = figlet.getFonts()
randomFont = fonts[random.randint(0, len(fonts))]
figlet.setFont(font=randomFont)

# Default: print user input's text with random font
if argc == 1:
	userInput = input("Input: ")
	print(figlet.renderText(userInput))

# If user specifies font and font exists in list of fonts
# then, print user input's text with Figlet font
# else, print error message
elif argc == 3:
	if sys.argv[1] in ["-f", "--font"] and sys.argv[2] in fonts:
		figlet.setFont(font=sys.argv[2])
		userInput = input("Input: ")
		print(figlet.renderText(userInput))
	else:
		print("Invalid usage")
else:
	print("Invalid usage")
