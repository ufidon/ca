### **Bit Pattern → Value:**

1. **Exponent Bias:**
   - The bias for a 2-bit exponent is $2^{2-1} - 1 = 1$.
   - The actual exponent is calculated as $e = E - \text{bias}$, where $E$ is the encoded exponent.

2. **Denormalized Numbers:**
   - For denormalized numbers ($E = 0$), the value is calculated as:
     $\text{Value} = (-1)^S \times 0.M \times 2^{1 - \text{bias}}$
     Here, $1 - \text{bias} = 0$, so the formula simplifies to:
     $\text{Value} = (-1)^S \times 0.M \times 2^{0} = (-1)^S \times 0.M$

3. **Normalized Numbers:**
   - For normalized numbers ($E \neq 0$ and $E \neq 3$), the value is calculated as:
     $\text{Value} = (-1)^S \times 1.M \times 2^{e}$
     where $e = E - \text{bias}$.

---

### **Example Calculations:**
1. Bit pattern: `01011`
   - $S = 0$ (positive)
   - $E = 10_2 = 2$
   - $M = 11_2 = 3$
   - Actual exponent: $e = 2 - 1 = 1$
   - Value: $1.11_2 \times 2^1 = 1.75 \times 2 = 3.5$

2. Bit pattern: `00011`
   - $S = 0$ (positive)
   - $E = 00_2 = 0$
   - $M = 11_2 = 3$
   - Denormalized: $0.11_2 \times 2^{0} = 0.75 \times 1 = 0.75$

3. Bit pattern: `11100`
   - $S = 1$ (negative)
   - $E = 11_2 = 3$
   - $M = 00_2 = 0$
   - Special case: $-\infty$
