package com.example.intelligentmeteringbasedk210.bean;

public class Send {
    private Integer cmd;
    private Float apple_p;
    private Float orange_p;
    private Float banana_p;

    @Override
    public String toString() {
        return "Send{" +
                "cmd=" + cmd +
                ", apple_p=" + apple_p +
                ", orange_p=" + orange_p +
                ", banana_p=" + banana_p +
                '}';
    }

    public Integer getCmd() {
        return cmd;
    }

    public void setCmd(Integer cmd) {
        this.cmd = cmd;
    }

    public Float getApple_p() {
        return apple_p;
    }

    public void setApple_p(Float apple_p) {
        this.apple_p = apple_p;
    }

    public Float getOrange_p() {
        return orange_p;
    }

    public void setOrange_p(Float orange_p) {
        this.orange_p = orange_p;
    }

    public Float getBanana_p() {
        return banana_p;
    }

    public void setBanana_p(Float banana_p) {
        this.banana_p = banana_p;
    }
}
