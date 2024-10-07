import re

#ejemplo con el punto (.)
pattern1 = r'c.t'
texto1 = "cat cot cut cit cgt cwt"
matches1 = re.findall(pattern1,texto1)
print("Patron'.':",matches1)

pattern2 = r'a'
texto2 = "aaa b aa b"
matches2 = re.findall(pattern2,texto2)
print("Patron'.':",matches2)

pattern3 = r'[A-Za-z0-9_]'
texto3 = "Kapumota1234_5 Username: Checha_gosht123"
matches3 = re.findall(pattern3,texto3)
print("Patron'[A-Za-z0-9_]':",matches3)

pattern4 = r'[^c]anana'
texto4 = "apple, canana, banana"
matches4 = re.findall(pattern4,texto4)
print("Patron'[^b]anana':",matches4)  # Salida: ['banana']

texto = "gooooal"
patron_asterisco = r"go*al"
patron_mas = r"go+al"

print(re.findall(patron_asterisco, texto))  # Salida: ['gooooal']
print(re.findall(patron_mas, texto))        # Salida: ['gooooal']

pattern8 = r'(ha)\1'
texto8 = "haha hah ha"
matches8 = re.findall(pattern8, texto8)
print(matches8)

texto = "foo_bar foo baz"
patron = r"(?<=foo_)\w+"
print(re.findall(patron, texto))  # Salida: ['bar']

patron = r"(?<!foo_)\w+"
print(re.findall(patron, texto))  # Salida: ['foo', 'baz']