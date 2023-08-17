Nodes = [];
class node():
    def __init__(self,type,inputs,output):
        self.type = type;
        self.inputs = inputs;
        self.value = None;
        self.output = output;
        if type == "AND" or type == "NAND":
            self.controlling_value = 0;
        elif type == "OR" or type == "NOR":
            self.controlling_value = 1;
        else:
            self.controlling_value = None;
        self.level = 0;
        for x in self.inputs:
            if Nodes[x].level >= self.level:
                self.level = Nodes[x].level + 1;
def initialize_PI(vector):
    i = 0;
    for x in Nodes:
        if x.type == "PI":
            x.value = bool(int(vector[i]));
            i+=1;
def get_output_vector():
    out = [1 for x in Nodes];
    for x in Nodes:
        for y in x.inputs:
            if x.output:
                out[y] = 1;
            else:
                out[y] = 0;
    vec = '';
    for x in range(len(out)):
        if out[x] == 1:
            vec+=str(int(Nodes[x].value));
    return vec;
def simulator(pi):
    initialize_PI(pi);
    for x in Nodes:
        if x.type == "AND":
            o = True;
            for i in x.inputs:
                o = o and Nodes[i].value;
            x.value = o;
        elif x.type == "OR":
            o = False;
            for i in x.inputs:
                o = o or Nodes[i].value;
            x.value = o;
        elif x.type == "XOR":
            o = False;
            for i in x.inputs:
                o = (o and (not(Nodes[i].value))) or ((not(o)) and Nodes[i].value);
            x.value = o;
        elif x.type == "NAND":
            o = True;
            for i in x.inputs:
                o = o and Nodes[i].value;
            x.value = not(o);
        elif x.type == "NOR":
            o = False;
            for i in x.inputs:
                o = o or Nodes[i].value;
            x.value = not(o);
        elif x.type == "XNOR":
            o = False;
            for i in x.inputs:
                o = (o and (not(Nodes[i].value))) or ((not(o)) and Nodes[i].value);
            x.value = not(o);
        elif x.type == "NOT":
            x.value = not(Nodes[x.inputs[0]].value);
        elif x.type == "PI":
            pass;
        else:
            print("One or more Gate type is invalid. Should be any of 'OR','AND','XOR','NAND','NOR','XNOR' or 'NOT'");
            return None;
    return get_output_vector();

def circuit(lines):
    for l in lines:
        s = l.split();
        type = s[1];
        if len(s)>2:
            if s[2]=="OUT":
                inputs = [int(s[i]) for i in range(3,len(s))];
                Nodes.append(node(type,inputs,True));
            elif s[2] != "OUT":
                inputs = [int(s[i]) for i in range(2,len(s))];
                Nodes.append(node(type,inputs,False));
            else:
                Nodes.append(node(type,[],True));
        else:
            Nodes.append(node(type,[],False));
if __name__ == "__main__":
    with open("Logic.txt") as f1:
        lines = f1.readlines();
        circuit(lines);
    with open("Testbench.txt") as f2:
        simulate = f2.readlines();
        for s in simulate:
            t = s.split();
            out = simulator(t[0])
            if out == t[1]:
                print("success");
            else:
                print("failure",t[1],out);