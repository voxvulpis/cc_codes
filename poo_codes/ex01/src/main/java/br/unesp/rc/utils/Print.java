package br.unesp.rc.utils;

import br.unesp.rc.modelo.Pessoa;

public class Print {
    public static void printFinal(Pessoa pessoa){
        System.out.println("\t" + pessoa.getNome());
        // System.out.println("\t\tSalário liq.: \t" + (pessoa.getSalario() - Imposto.calculo(pessoa)));
        System.out.println("\t\tSalário liq.: \t" + Imposto.salarioLiquido(pessoa));
        System.out.println("\t\tImposto: \t" + Imposto.calculo(pessoa));
        System.out.println("\t\tSalário bruto: \t" + pessoa.getSalario());
    }
}
