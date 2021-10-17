import java.util.*;
import java.io.*;

public class DFA {
    public final Integer totalSymbols;
    public final Integer totalStates;
    public final Integer startState;
    public final Set<Integer> finalStates;
    public final Map<Character, Integer> transitions[];

    public DFA(
        Integer totalSymbols,
        Integer totalStates,
        Integer startState,
        Set<Integer> finalStates,
        Map<Character, Integer> transitions[]
    ) {
        assert startState < totalStates;
        assert Collections.max(finalStates) < totalStates;
        assert transitions.length <= totalStates;

        this.totalSymbols = totalSymbols;
        this.totalStates = totalStates;
        this.startState = startState;
        this.finalStates = finalStates;
        this.transitions = transitions;
    }

    public static DFA readFrom(String filename) {
        Set<Integer> finalStates = new HashSet<>();
        Scanner scanner;

        try {
            scanner = new Scanner(new FileReader(filename));
        } catch (FileNotFoundException exception) {
            System.err.println("File not found.");
            return null;
        }

        Integer totalSymbols = scanner.nextInt();
        Integer totalStates = scanner.nextInt();
        Integer startState = scanner.nextInt();
        Integer totalFinalStates = scanner.nextInt();

        @SuppressWarnings("unchecked")
        Map<Character, Integer> transitions[] = new HashMap[totalStates];

        for (int i = 0; i < totalStates; i++) {
            transitions[i] = new HashMap<>();
        }

        for (int i = 0; i < totalFinalStates; i++) {
            finalStates.add(scanner.nextInt());
        }

        while (scanner.hasNext()) {
            Integer from = scanner.nextInt();
            Character symbol = scanner.next().charAt(0);
            Integer to = scanner.nextInt();
            transitions[from].put(symbol, to);
        }

        scanner.close();

        return new DFA(totalSymbols, totalStates, startState, finalStates, transitions);
    }

    public boolean isFinal(Integer state) {
        return finalStates.contains(state);
    }
}
