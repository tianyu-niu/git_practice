// Online Java Compiler
// Use this editor to write, compile and run your Java code online
public class A1_NIU {
    public static int peak(int[] a) {
        if (a == null || a.length == 0) {
            return -1;
        }
        int i = 0;
        while (i < a.length - 1 && a[i] < a[i + 1]) {
            i++;
        }
        return i;
    }
}