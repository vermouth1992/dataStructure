import leetCodeUtility.ListNode;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by chizhang on 6/12/16.
 */
public class leetCodeUtilityTest {
    @Test
    public void testListNodeEqual() {
        int[] a = {1, 2, 3, -4, 5};
        ListNode h1 = new ListNode(a);
        ListNode h2 = new ListNode(a);
        assertEquals(h1, h2);
    }
}
