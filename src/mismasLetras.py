import sys
from string import ascii_lowercase

def repeat_string(list, times):
    repeated_string = list * times
    return repeated_string

def save_to_file(filename, content):
    with open(filename, 'w') as file:
        for word in content:
            file.write(word + '\n')

def add_word(strings):
    for letra1 in ascii_lowercase:
        for letra2 in ascii_lowercase:
            for letra3 in ascii_lowercase:
                res = "b{}{}{}".format(letra1,letra2,letra3)
                strings.append(res)


    




def main(reps, filename):
    strings = ['a']
    add_word(strings)
    # repeated_string = repeat_string(string, reps)
    long = len(strings)
    save_to_file("data/"+filename+"-"+str(long), strings)

if __name__ == '__main__':
    rep = int(sys.argv[1])
    filename = sys.argv[2]
    main(rep, filename)
