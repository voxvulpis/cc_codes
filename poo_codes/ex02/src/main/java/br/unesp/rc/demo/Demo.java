package br.unesp.rc.demo;

import br.unesp.rc.modelo.Curso;
import br.unesp.rc.repositorio.CursoRep;

public class Demo {
    
    public static void RunEx(){
        System.out.println("Test 1");
        System.out.print("\033[H\033[2J");  
        System.out.flush();

        System.out.println("Demo Start.");

        String[] cods = {"pri", "sec", "ter", "quad"};
        int[] vgs = {21, 22, 23, 24};
        int[] candMs = {151, 162, 173, 184};
        int[] candFs = {31, 242, 34, 184};

        CursoRep cursos = new CursoRep(cods, vgs, candMs, candFs);

        for (Curso i : cursos.getCursos()) {
            System.out.println("Curso:" 
                + "\n\tCod:\t\t"        + i.getCod()
                + "\n\tVagas:\t\t"      + i.getVagas()
                + "\n\tCand. Masc:\t"   + i.getCandM()
                + "\n\tCand. Fem.:\t"   + i.getCandF());
        }
    }
}
