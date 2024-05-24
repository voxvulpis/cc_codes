package br.unesp.model;

import java.lang.reflect.Field;
import java.net.MalformedURLException;

import br.unesp.utils.ClassExtractor;

public class SqlString {
    // private String path;
    // private String className;
    private ClassExtractor classExtractor;
    // private String classFields[];
    // private String classMethods[];
    private final String comaString = ", ";
    private StringBuilder sqlBuilder;
    private int fieldCounter = 0;
    
    
    public SqlString(String path, String className) throws MalformedURLException, ClassNotFoundException {
        this.classExtractor = new ClassExtractor(path, className);
        // this.classFields = classExtractor.getFields().toString().

        sqlBuilder.append("INSERT INTO Address (");

        for(Field f : classExtractor.getFields()){
            fieldCounter++;
            sqlBuilder.append(f.getName()).append(comaString);
        }

        sqlBuilder.append(") VALUES (");

        for(int i = 0; i < fieldCounter; i++){
            sqlBuilder.append("?").append(comaString);
        }
        sqlBuilder.append(")");

    }

    
}
