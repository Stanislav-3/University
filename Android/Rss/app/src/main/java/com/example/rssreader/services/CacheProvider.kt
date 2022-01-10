package com.example.rssreader.services

import android.content.Context
import com.example.rssreader.models.Article
import com.squareup.moshi.Moshi
import com.squareup.moshi.Types

class CacheProvider {

    companion object {

        private const val articlesCache = "articles_cache"
        private const val rssFeedUrl = "rss_feed_url"
        private const val CONTEXT_NAME = "AppCache"

        private val moshi = Moshi.Builder().build()
        private val adapter =
            moshi.adapter<List<Article>>(Types.newParameterizedType(List::class.java, Article::class.java))

        private fun dumps(data: List<Article>) = adapter.toJson(data)
        private fun loads(data: String) = adapter.fromJson(data)

        fun saveArticlesToCache(context: Context, data: List<Article>, url: String) {
            val sharedPreferences = context.getSharedPreferences(CONTEXT_NAME, Context.MODE_PRIVATE)
            val jsonedArticleList = dumps(data)
            val editor = sharedPreferences.edit()
            editor.putString(articlesCache ,jsonedArticleList)
            editor.putString(rssFeedUrl, url)
            editor.apply()
        }

        fun loadArticlesListFromCache(context: Context): List<Article> {
            val sharedPreferences = context.getSharedPreferences(CONTEXT_NAME, Context.MODE_PRIVATE)
            val jsonedArticleList = sharedPreferences.getString(articlesCache, null)
            return jsonedArticleList?.let { loads(it) } ?: listOf()
        }

        fun loadUrlFromCache(context: Context): String {
            val sharedPreferences = context.getSharedPreferences(CONTEXT_NAME, Context.MODE_PRIVATE)
            return sharedPreferences.getString(rssFeedUrl, null).toString()
        }

    }

}