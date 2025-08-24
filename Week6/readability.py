from cs50 import get_string

# Get input from the user
text = get_string("Text: ")

# Counts Letters
letter_count = sum(1 for letter in text if letter.isalpha())

# Counts Words
word_count = len(text.split())

# Counts Sentences
sentence_count = sum(1 for char in text if char in ['.', '?', '!'])

# Calculates average per 100 words
L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100

# Calculate Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)

# Output Grade Level
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
