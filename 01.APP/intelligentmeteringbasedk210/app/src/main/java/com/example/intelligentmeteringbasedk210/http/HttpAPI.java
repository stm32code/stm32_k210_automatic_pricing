package com.example.intelligentmeteringbasedk210.http;


import com.example.intelligentmeteringbasedk210.bean.EquipmentData.Equipment0nline;
import com.example.intelligentmeteringbasedk210.bean.EquipmentData.EquipmentBean;
import com.example.intelligentmeteringbasedk210.utils.Common;

import retrofit2.Call;
import retrofit2.http.GET;
import retrofit2.http.Headers;

public interface HttpAPI {
    // OneNET 数据
    @Headers("api-key:" + Common.api_key)
    @GET(Common.Drive2ID + "/datapoints?limit=100")
    Call<EquipmentBean> getEquipmentData();

    // OneNET 设备状态
    @Headers("api-key:" + Common.api_key)
    @GET(Common.Drive2ID)
    Call<Equipment0nline> getEquipmentonline();
}
