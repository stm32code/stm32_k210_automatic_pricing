package com.example.intelligentmeteringbasedk210.bean;

public class DataGram {
    private String at;
    private String value;

    @Override
    public String toString() {
        return "DataGram{" +
                "at='" + at + '\'' +
                ", value='" + value + '\'' +
                '}';
    }

    public String getAt() {
        return at;
    }

    public void setAt(String at) {
        this.at = at;
    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
