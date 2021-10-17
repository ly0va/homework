import java.util.*;

public class Lab2 {
    public static void main(String[] args) {
        DFA first = DFA.readFrom("dfa1.txt");
        DFA second = DFA.readFrom("dfa2.txt");
        
        if (equivalent(first, second)) {
            System.out.println("DFAs are equivalent!");
        } else {
            System.out.println("DFAa are NOT equivalent!");
        }
    }

    public static boolean equivalent(DFA dfa1, DFA dfa2) {
        Integer totalSymbols = Math.max(dfa1.totalSymbols, dfa2.totalSymbols);
        boolean used[][] = new boolean[dfa1.totalStates][dfa2.totalStates];

        Queue<Map.Entry<Integer, Integer>> queue = new LinkedList<>();
        queue.add(Map.entry(dfa1.startState, dfa2.startState));

        while (!queue.isEmpty()) {
            Map.Entry<Integer, Integer> uv = queue.poll();
            Integer u = uv.getKey(), v = uv.getValue();
            used[u][v] = true;

            if (dfa1.isFinal(u) != dfa2.isFinal(v)) {
                return false;
            }

            for (char c = 'a'; c < 'a' + totalSymbols; c++) {
                Integer newU = dfa1.transitions[u].get(c);
                Integer newV = dfa2.transitions[v].get(c);
                if (newU == null && newV == null) {
                    continue;
                }
                if (newU == null || newV == null) {
                    return false;
                }
                if (!used[newU][newV]) {
                    queue.add(Map.entry(newU, newV));
                }
            }
        }

        return true;
    }
}
