//
//  TestForList.h
//  testProgram
//
//  Created by Chi Zhang on 8/1/15.
//  Copyright (c) 2015 Chi Zhang
/*
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 General Public License as published by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 License for more details.
 You should have received a copy of the GNU General Public License along with this program; if not, write
 to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 If you have any questions, please email zhan527@usc.edu
*/

#ifndef __testProgram__TestForList__
#define __testProgram__TestForList__

#include <stdio.h>

void testForList()
{
    //test constructor
    List<int> L;
    L.insertAsFirst(10);
    L.insertAsFirst(5);
    L.insertAsLast(20);
    ListNode<int> *p = L.first();
    L.insertBefore(p, 15);
    p = p->succ;
    L.insertBefore(p, 12); //p can't self repoint to L.first()
    L.insertAfter(p, 15);
    List<int> L1(L);   //copy entire List
    L1.showList();
    List<int> L2(L1, 2, 3); //copy from particular rank
    L2.showList();
    List<int> L3(p, 3);     //copy from particular ListNode
    L3.showList();
    cout << L.size() << ' ' << L.empty() << endl;
    cout << L.disordered() << endl;
    //test find
    L.showList();
    ListNode<int>* q;
    q = L.find(10);
    cout << q->succ->data << endl;
    q = L.find(15, 3, q);  //start find 15 from 10
    cout << q->succ->data << endl;
    List<int> L4(L);
    L.deduplicate();  //test 无序去重
    L.showList();
    //test sort
    L.sort();
    L.showList();
    cout << "List4 test" << endl;
    L4.sort();
    L4.showList();
    L4.uniquify();
    L4.showList();
    //test for search
    q = L4.search(9);
    cout << q->data << endl;
    cout << L4.selectMax()->data << endl;
}


#endif /* defined(__testProgram__TestForList__) */
