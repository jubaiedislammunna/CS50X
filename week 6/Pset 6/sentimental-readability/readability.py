from cs50 import get_string

# Prompt user for text using a get_string command.

text = get_string("Text: \n")

# Count the number of letters per one-hundred words in the text:

l = 0
w = 1
s = 0

for i in range(len(text)):
    if text[i].isalpha():
        l += 1

    if text[i] == " ":
        w += 1

    if text[i] == "!" or text[i] == "?" or text[i] == ".":
        s = s + 1


X = (l / w) * 100
Y = (s / w) * 100

grade_level = round(0.0588 * X - 0.296 * Y - 15.8)

if grade_level < 1:
    print("Before Grade 1")

elif grade_level > 16:
    print("Grade 16+")

# Print out ("Grade X"), where X is the result of (0.0588 * 2a - 0.296 * 3a - 15.8)

else:
    print("Grade ", grade_level)
