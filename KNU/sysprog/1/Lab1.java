// Потьомкiн Лев, Лабораторна 1, Варiант 9

import java.io.*;
import java.util.*;

public class Lab1 {
    public static void main(String[] args) {
        List<String> words = readWords("file.txt");
        if (words != null) {
            for (String word: mostDiverseWords(words)) {
                System.out.println(word);
            }
        }
    }

    public static List<String> readWords(String filename) {
        List<String> words = new ArrayList<String>();
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
                words.add(word);
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

    public static List<String> mostDiverseWords(List<String> words) {
        List<String> result = new ArrayList<String>();
        if (words.isEmpty()) {
            return result;
        }

        Collections.sort(words, (a, b) -> countLetters(b).compareTo(countLetters(a)));
        Integer maxDifferentLetters = countLetters(words.get(0));

        for (String word: words) {
            if (countLetters(word) == maxDifferentLetters) {
                result.add(word);
            } else {
                break;
            }
        }

        return result;
    }
}
