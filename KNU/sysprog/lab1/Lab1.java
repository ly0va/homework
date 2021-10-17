// Потьомкiн Лев, Лабораторна 1, Варiант 9

import java.io.*;
import java.util.*;

public class Lab1 {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Filename not specified");
            return;
        }

        Set<String> words = readWords(args[1]);

        if (words != null) {
            for (String word: words) {
                System.out.println(word);
            }
        }
    }

    public static Set<String> readWords(String filename) {
        Set<String> words = new HashSet<String>();
        Scanner scanner;

        try {
            scanner = new Scanner(new FileReader(filename));
        } catch (FileNotFoundException exception) {
            System.out.println("File not found.");
            return null;
        }

        while (scanner.hasNext()) {
            String line = scanner.nextLine();
            for (String word: line.split("\\W+")) {
                int letters = countLetters(word);
                if (words.isEmpty() || countLetters(words.toArray()[0].toString()) < letters) {
                    words.clear();
                }
                if (words.isEmpty() || countLetters(words.toArray()[0].toString()) == letters) {
                    words.add(word);
                }  
            }
        }

        scanner.close();
        return words;
    }
    
    public static Integer countLetters(String word) {
        Set<Character> unique = new HashSet<Character>();
        for (char letter: word.toLowerCase().toCharArray()) {
            unique.add(letter);
        }
        return unique.size();
    }
}
