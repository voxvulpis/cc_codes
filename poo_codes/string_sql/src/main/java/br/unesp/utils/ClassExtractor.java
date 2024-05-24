package br.unesp.utils;

import java.io.File;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;

public class ClassExtractor {
    // private String path;
    // private String className;
    // private StringBuilder classFields;
    // private StringBuilder classMethods;

    // private String pathToFile;
    File file;
    URL url;
    URLClassLoader classLoader;
    @SuppressWarnings("rawtypes")
    Class clazz;
    Field fields[];
    @SuppressWarnings("rawtypes")
    Constructor constructs[];
    
    
    public ClassExtractor(String path, String className) throws MalformedURLException, ClassNotFoundException {
        // this.path = path;
        // this.className = className;
        // this.classMethods = new StringBuilder();
        // this.classFields = new StringBuilder();

        this.file = new File(path);
        this.url = file.toURI().toURL();
        this.classLoader = new URLClassLoader(new URL[]{url});
        this.clazz = classLoader.loadClass(className);

        this.fields = clazz.getDeclaredFields();
        this.constructs = clazz.getConstructors();

    }


    // public File getFile() {
    //     return file;
    // }


    // public URL getUrl() {
    //     return url;
    // }


    // public URLClassLoader getClassLoader() {
    //     return classLoader;
    // }


    // public Class getClazz() {
    //     return clazz;
    // }


    public Field[] getFields() {
        return fields;
    }


    @SuppressWarnings("rawtypes")
    public Constructor[] getConstructs() {
        return constructs;
    }

    
    

}
