package leetCodeUtility;

import org.junit.Test;
import static org.junit.Assert.*;

import java.util.List;

/**
 * Created by chizhang on 6/12/16.
 */
public class ListNode {
    public int val;
    public ListNode next;

    public ListNode() {
        this(0);
    }

    public ListNode(int x) {
        val = x;
        next = null;
    }

    public ListNode(int[] l) {
        ListNode ptr = null;
        for (int i = 0; i < l.length; i++) {
            if (i == 0) {
                this.val = l[i];
                ptr = this;
            } else {
                ptr.next = new ListNode(l[i]);
                ptr = ptr.next;
            }
        }
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ListNode listNode = (ListNode) o;

        if (val != listNode.val) return false;
        return next != null ? next.equals(listNode.next) : listNode.next == null;

    }

    @Override
    public int hashCode() {
        int result = val;
        result = 31 * result + (next != null ? next.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        String result = "";
        ListNode ptr = this;
        while (ptr != null) {
            result = result + ptr.val;
            ptr = ptr.next;
            if (ptr != null) result += " -> ";
        }
        return result;
    }





    public static void main(String[] args) {
        int[] a = {1, 2, 3, -4, 5};
        ListNode head = new ListNode(a);
        System.out.println(head);
        // jh61b.junit.TestRunner.runTests("all", ListNode.class);
    }

}
