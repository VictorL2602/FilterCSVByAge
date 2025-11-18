# Filter CSV by Age

Dette program filtrerer linjer fra en CSV-fil og udskriver kun dem hvor alderen er mindre end eller lig med en angivet maksimumalder. Programmet håndterer både input/output-filer og standard input/output.

Fejlmeddelelser bliver skrevet til **stderr**, mens gyldige CSV-linjer bliver skrevet til **stdout** eller en angivet outputfil.

# Brug af programmet

Efter kompilering kan man sortere sin csv fil således:
./main.exe max-age input-file output-file

# Eksempler

Hvis man hvis skrive sin sorterede csv fil til en ny csv fil, gøres det således:
./main.exe 30 people-with-age.csv result.csv

Hvis man vil printe til terminalen, gøres det således:
./main.exe 30 people-with-age.csv

Hver linje skal være: Navn, Alder

# Funktion

-Læser linjen med fgets
-Splitter navn/alder med strtok
-Læser aldersfeltet som et tal med sscanf
-Printer kun gyldige linjer
-Virker både med filer og stdin/stdout