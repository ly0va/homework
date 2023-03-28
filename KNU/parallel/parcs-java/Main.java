import parcs.*;
import java.io.*;
import java.util.*;
import java.math.BigDecimal;

public class Main implements AM {
    public static void main(String[] args) {
        task t = new task();
        t.addJarFile("Pi.jar");
        new Main().run(new AMInfo(t, (channel)null));
        t.end();
    }

    public void run(AMInfo info) {
      Scanner in = new Scanner(System.in);
      int n = in.nextInt();
      int workers = in.nextInt();
      int step = (n - 1) / workers + 1;

      ArrayList<channel> channels = new ArrayList<channel>();

      for (int k = 0; k < n; k += step) {
        point p = info.createPoint();
        channel c = p.createChannel();
        channels.add(c);
        p.execute("Pi");
        c.write(n);
        c.write(k);
        c.write(k + step);
      }

      System.out.println("Computing...");

      BigDecimal sum = BigDecimal.ZERO;
      for (int i = 0; i < channels.size(); i++) {
        BigDecimal part = (BigDecimal)channels.get(i).readObject();
        sum = sum.add(part);
      }

      System.out.println("Done.\n");
      System.out.println("Pi = " + sum);
    }
}
