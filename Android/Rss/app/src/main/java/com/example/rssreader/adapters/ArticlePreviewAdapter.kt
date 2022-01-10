package com.example.rssreader.adapters

import android.graphics.Color
import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.navigation.findNavController
import androidx.recyclerview.widget.RecyclerView
import com.example.rssreader.databinding.ArticlePreviewLayoutAdapterBinding
import com.example.rssreader.fragments.HomeFragmentDirections
import com.example.rssreader.models.Article
import com.squareup.picasso.Picasso

class ArticlePreviewAdapter: RecyclerView.Adapter<ArticlePreviewAdapter.ArticlePreviewViewHolder>() {

    class ArticlePreviewViewHolder(val itemBinding: ArticlePreviewLayoutAdapterBinding): RecyclerView.ViewHolder(itemBinding.root)

    var articles = mutableListOf<Article>()

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ArticlePreviewViewHolder {
        return ArticlePreviewViewHolder(ArticlePreviewLayoutAdapterBinding.inflate(LayoutInflater.from(parent.context), parent, false))
    }

    override fun onBindViewHolder(holder: ArticlePreviewViewHolder, position: Int) {
        val currentArticlePreview = articles[position]
        holder.itemBinding.tvTitle.text = currentArticlePreview.title
        holder.itemBinding.tvDescription.text = currentArticlePreview.description
        holder.itemBinding.tvPubDate.text = currentArticlePreview.pubDate
        if (currentArticlePreview.image.isNotEmpty()) {
            Picasso.get().load(currentArticlePreview.image).into(holder.itemBinding.ivImage)
        } else {
            val random = java.util.Random()
            val color = Color.argb(255,
                random.nextInt(256),
                random.nextInt(256),
                random.nextInt(256)
            )
            holder.itemBinding.ivImage.setColorFilter(color)
        }
        holder.itemView.setOnClickListener { view ->
            val direction = HomeFragmentDirections.actionHomeFragmentToArticleFragment(currentArticlePreview)
            view.findNavController().navigate(direction)
        }
    }

    override fun getItemCount(): Int {
        return articles.size
    }
}