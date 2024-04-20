package br.unesp.rc.utils;

import br.unesp.rc.modelo.Pessoa;

public class Imposto {
    public static Float categoria(Pessoa pessoa){
        Float value = 0.0f;
        Float sal = pessoa.getSalario();

        if (sal > 4000f) {
            value = 27.5f;
        } else if(sal > 3000){
            value = 22.5f;
        } else if(sal > 2000f){
            value = 15f;
        } else if(sal > 1500f){
            value = 7.5f;
        }
        
        return value;
    }

    public static Float calculo(Pessoa pessoa){

        return pessoa.getSalario()/100 * categoria(pessoa);
    }

    public static Float salarioLiquido(Pessoa pessoa){
        return pessoa.getSalario() - calculo(pessoa);
    }
}
