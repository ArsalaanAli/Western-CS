
def factorial(n):
    result = n
    for i in range(n-1, 0, -1):
        result*=i
    return result

print(factorial(4))


def countVowels(word):  
  numVowels = 0
  for letter in word:  
      if letter.lower() in "aeiou":
          numVowels+=1
  return numVowels  

print(countVowels("AEIOu"))
