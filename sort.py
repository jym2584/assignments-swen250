def sort(string):
    list2 = string.split(" ")
    print(len(list2))
    string = ""
    listnum = []
    for i in range(0, len(list2)-1):
        listnum.append(int(list2[i]))
        string += list2[i] + " " 
        print(i + 1)

    listnum.sort()
    print(string)
    print(listnum)

sort("130 55 45 64 155 66 60 80 102 62 58 101 75 111 151 139 81 55 66 90 97 77 51 67 125 50 136 55 83 91 54 86 100 78 93 113 111 104 96 113 96 87 129 109 69 94 99 97 83 97")