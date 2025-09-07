package com.example.intelligentmeteringbasedk210.bean;

public class Receive {
    private String wight;
    private String apple_p;
    private String orange_p;
    private String banana_p;

    @Override
    public String toString() {
        return "Receive{" +
                "wight='" + wight + '\'' +
                ", apple_p='" + apple_p + '\'' +
                ", orange_p='" + orange_p + '\'' +
                ", banana_p='" + banana_p + '\'' +
                '}';
    }

    public String getWight() {
        return wight;
    }

    public void setWight(String wight) {
        this.wight = wight;
    }

    public String getApple_p() {
        return apple_p;
    }

    public void setApple_p(String apple_p) {
        this.apple_p = apple_p;
    }

    public String getOrange_p() {
        return orange_p;
    }

    public void setOrange_p(String orange_p) {
        this.orange_p = orange_p;
    }

    public String getBanana_p() {
        return banana_p;
    }

    public void setBanana_p(String banana_p) {
        this.banana_p = banana_p;
    }
}
