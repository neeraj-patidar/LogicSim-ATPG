Netlist file should be named as "Logic.txt"(else slight modifications required in the code)
Netlist format:
<node no> <type of operation to get output> <*OUT> <*input node0> <*input node1> <*input node2> <*input node3>.......
1) start node no. from 0
2) node no should be defined serially i.e node 0 should be defined first then node 1 and so on
3) a node which is not defined can't be used as input to any other node
4) type of operation shuld be one of "OR","AND","XOR","NOR","NAND","XNOR","NOT","PI".
   "PI" isn't any logical operation but states that this node is a primary input node and 
    format for such nodes is '<node no> PI'
5) By default, nodes which aren't input to any other operation are considered output nodes. If you want to
   get output of a node which is also an input to another operation, then "OUT" should be given as 3rd parameter while defining
   that node in  netlist.
6) * marked parameters(other than"OUT") are valid for all operation type except "PI".
   if operation type is "NOT", then only <input node0> is required specifying more than one input will assume them ineffective and 
   inversion of <input node0> will be considered as output of the operation.
7) for logical operations OR,AND,XOR,NOR,NAND,XNOR atleast 2 input nodes required else output will be same as input, and these operations can be performed for n inputs too.

Input/output format: (This file should be named as "Testbench.txt"(else small modif reqd))
Each line of the file have a input and output vectors sepearated by " ".
format:
<input vector> <expected output vector>
<input vector>: values should be 0(False) or 1(True) and arranged in ascending order of node no.
<output vector>: values should be 0(False) or 1(True) and arranged in ascending order of node hno.