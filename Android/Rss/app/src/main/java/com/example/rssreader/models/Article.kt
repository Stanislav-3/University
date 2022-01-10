package com.example.rssreader.models

import android.os.Parcelable
import com.squareup.moshi.JsonClass
import kotlinx.parcelize.Parcelize

@JsonClass(generateAdapter = true)
@Parcelize
data class Article (
    val title: String,
    val description: String,
    val image: String,
    val pubDate: String,
    val content: String,
    val link: String
) : Parcelable
