package com.example.intelligentmeteringbasedk210.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

import com.example.intelligentmeteringbasedk210.bean.DataGram;
import com.example.intelligentmeteringbasedk210.databinding.RecordListviewItemBinding;

import java.util.List;

public class RecordListViewAdapter extends BaseAdapter {
    private Context context;
    private List<Object> list;

    public RecordListViewAdapter(Context context, List<Object> list) {
        this.context = context;
        this.list = list;
    }

    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int i) {
        return list.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }


    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        ViewHolder holder;
        if (view == null) {
            RecordListviewItemBinding binding = RecordListviewItemBinding.inflate(LayoutInflater.from(context), viewGroup, false);
            view = binding.getRoot();
            holder = new ViewHolder(binding);
            view.setTag(holder);
        } else {
            holder = (ViewHolder) view.getTag();
        }
        initView(holder, i);
        return view;

    }


    private void initView(ViewHolder holder, int i) {
        DataGram record = (DataGram) list.get(i);
        holder.binding.dateTimeText.setText(record.getAt());
        holder.binding.priceText.setText(record.getValue());
    }


    private class ViewHolder {
        private RecordListviewItemBinding binding;

        private ViewHolder(RecordListviewItemBinding binding) {
            this.binding = binding;
        }
    }
}
