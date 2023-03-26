import java.math.BigDecimal;
import java.math.RoundingMode;

import parcs.*;

public class Pi implements AM {
    public void run(AMInfo info) {
        int precision = info.parent.readInt();
        int from = info.parent.readInt();
        int upto = info.parent.readInt();

		BigDecimal sum = BigDecimal.ZERO;
		
		for (int k = from; k < upto; k++) {
			BigDecimal part = partialSum(k, precision).divide(new BigDecimal(16).pow(k), precision, RoundingMode.DOWN);
			sum = sum.add(part);
		}
		
        info.parent.write(sum);
	}
	
	BigDecimal partialSum(int k, int precision) {
        BigDecimal eightK = new BigDecimal(8).multiply(new BigDecimal(k));
		
		BigDecimal term1 = new BigDecimal(4).divide(eightK.add(new BigDecimal(1)), precision, RoundingMode.DOWN);
		BigDecimal term2 = new BigDecimal(2).divide(eightK.add(new BigDecimal(4)), precision, RoundingMode.DOWN);
		BigDecimal term3 = new BigDecimal(1).divide(eightK.add(new BigDecimal(5)), precision, RoundingMode.DOWN);
		BigDecimal term4 = new BigDecimal(1).divide(eightK.add(new BigDecimal(6)), precision, RoundingMode.DOWN);
		
		return term1.subtract(term2).subtract(term3).subtract(term4);
	}
}
