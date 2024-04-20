package br.unesp.rc.demo;

import br.unesp.rc.modelo.Pessoa;
import br.unesp.rc.utils.Print;

public abstract class Demo {
    public static void demo(){
        Pessoa p1 = new Pessoa("ps1", "cpf1", 501f);
        Pessoa p2 = new Pessoa("ps2", "cpf2", 1501f);
        Pessoa p3 = new Pessoa("ps3", "cpf3", 2501f);
        Pessoa p4 = new Pessoa("ps4", "cpf4", 3501f);
        Pessoa p5 = new Pessoa("ps5", "cpf5", 4501f);

        Print.printFinal(p1);
        Print.printFinal(p2);
        Print.printFinal(p3);
        Print.printFinal(p4);
        Print.printFinal(p5);

        // System.out.println("Debug:\n");
    }
}
