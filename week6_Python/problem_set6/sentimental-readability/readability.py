def get_text():
    while True:
        text = input("Text: ")
        if len(text) > 1:
            return text
        else:
            print("Invalid input.")


def count_letter(n):
    counter_letter = 0
    for i in range(len(n)):
        if n[i].isalnum():
            counter_letter += 1
    return counter_letter


def count_words(n):
    words = n.split()
    return len(words)


def count_sentences(n):
    counter_sentences = 0
    for i in range(len(n)):
        if n[i] == "?" or n[i] == "!" or n[i] == ".":
            counter_sentences += 1
    return counter_sentences


def calculate_colemanLaiuIndex(counter_letter, counter_sentences, word_count):
    L = float(counter_letter / word_count * 100)
    S = float(counter_sentences / word_count * 100)
    index = round(0.0588 * L - 0.296 * S - 15.8)
    return index


def main():
    text = get_text()
    letter_count = count_letter(text)
    word_count = count_words(text)
    sentence_count = count_sentences(text)
    index = calculate_colemanLaiuIndex(letter_count, sentence_count, word_count)

    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {round(index)}")

if __name__ == "__main__":
    main()
