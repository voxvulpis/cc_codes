package br.unesp.rc.repositorio;

import java.util.ArrayList;

import br.unesp.rc.modelo.Curso;

public class CursoRep {
    // public static void print
    private ArrayList<Curso> cursos;

    public CursoRep() {
        cursos = new ArrayList<>();
    }

    public CursoRep(String cods[], int vgs[], int candMs[], int candFs[]) {

        cursos = new ArrayList<>();
        
        for(int i = 0; i < cods.length; i++){
            try {
                cursos.add(new Curso(cods[i], vgs[i], candMs[i], candFs[i]));
            } catch (Exception e) {
                System.out.println("[DEBUG] \'addCurso\' :\n" + e);
            }
            
        }
    }

    public ArrayList<Curso> getCursos() {
        return cursos;
    }

    
    

}
