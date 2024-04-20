package br.unesp.rc.utils;

import java.util.List;

import br.unesp.rc.modelo.Curso;

public abstract class CursoUtils {
    public static void maiorConcorrencia(List<Curso> list){
        Float concorrencia = 0f;
        for (Curso curso : list) {
            if (concorrencia <= curso.getCandPorVaga()) {
                
            }
            
        }
    }
}
