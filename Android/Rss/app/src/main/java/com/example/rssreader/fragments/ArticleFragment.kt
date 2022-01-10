package com.example.rssreader.fragments

import android.R.attr
import android.content.Intent
import android.content.res.Configuration
import android.os.Bundle
import android.view.*
import android.webkit.*
import androidx.fragment.app.Fragment
import androidx.navigation.findNavController
import androidx.navigation.fragment.navArgs
import com.example.rssreader.MainActivity
import com.example.rssreader.R
import com.example.rssreader.databinding.FragmentArticleBinding
import com.example.rssreader.network.NetworkStateReceiver
import android.R.attr.data
import java.util.ArrayList


class ArticleFragment : Fragment(R.layout.fragment_article) {

    private var _binding: FragmentArticleBinding? = null
    private val binding get() = _binding!!
    private val args: ArticleFragmentArgs by navArgs()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)
        (activity as MainActivity).supportActionBar?.setDisplayHomeAsUpEnabled(true)
        (activity as MainActivity).supportActionBar?.setDisplayShowHomeEnabled(true)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentArticleBinding.inflate(inflater, container, false)

        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        setUpWebView()
    }

    @JavascriptInterface
    fun isNightMode(): Boolean {
        val nightModeFlags = resources.configuration.uiMode and Configuration.UI_MODE_NIGHT_MASK
        return nightModeFlags == Configuration.UI_MODE_NIGHT_YES
    }

    private fun setUpWebView() {
        binding.webView.settings.loadWithOverviewMode = true
        binding.webView.settings.javaScriptEnabled = true
        binding.webView.webChromeClient = WebChromeClient()
        binding.webView.goBackOrForward(0)

        if (NetworkStateReceiver().isConnectedOrConnecting(context)) {
            val url = args.article?.link.toString()
            binding.webView.setWebViewClient(object : WebViewClient() {
                override fun shouldOverrideUrlLoading(
                    view: WebView?,
                    request: WebResourceRequest
                ): Boolean {
//                    var redirectToOtherApp = true
//                    var baseUrl = args.article?.link.toString().split('/')
//                    if (request.url.toString().contains(baseUrl[2])) {
//                    if (!request.url.toString().contains("share")) {
//                        return true
//                    } else {
                        var apps = activity!!.packageManager.getInstalledPackages(0)
                        for (i in 0 until apps.size) {
                            var name = apps.get(i).applicationInfo.loadLabel(activity!!.packageManager).toString()
                            if (request.url.toString().lowercase().contains(name.lowercase()) ||
                                (name.lowercase() == "telegram" && request.url.toString().lowercase().contains("t.me"))) {
                                Intent(Intent.ACTION_VIEW, request.url).apply {
                                    startActivity(this)
                                }
                            }
                        }
//                    }
                    return true
                }
            })
            binding.webView.loadUrl(url)
            //        binding.webView.setWebViewClient(object : WebViewClient() {
//            override fun shouldOverrideUrlLoading(
//                view: WebView?,
//                request: WebResourceRequest
//            ): Boolean {
//                var redirectToOtherApp = false
//                var apps = activity!!.packageManager.getInstalledPackages(0)
//                for (i in 0 until apps.size) {
//                    var name = apps.get(i).applicationInfo.loadLabel(activity!!.packageManager).toString()
//                    if (request.url.toString().lowercase().contains(name.lowercase())) {
//                        redirectToOtherApp = true
//                        break
//                    }
//                }
//                return if (redirectToOtherApp) {
//                    super.shouldOverrideUrlLoading(view, request)
//                } else {
//                    return true
//                }
//            }
//        })
        } else {
            binding.webView.setBackgroundColor(0)
            var color = ""
            if (isNightMode()) {
                color = "white"
            } else {
                color = "black"
            }

            var mainContent = args.article?.content
            if (mainContent.isNullOrEmpty()) {
                mainContent = args.article?.description
            }
            val htmlData = "<style>img{display: inline; height: auto; max-width: 100%;}</style>\n" +
                    "<style>iframe{ height: auto; width: auto;}</style>\n" +
                    "<h1 style=\"color: ${color}\">" + args.article?.title + "</h1>" +
                    "<h6 align=\"right\" style=\"color: ${color}\">" + args.article?.pubDate + "</h6>" +
                    "<img src=\"" + args.article?.image + "\" alt=\"Image Preview\">" +
                    "<div style=\"color: ${color}\">" + mainContent + "</div>"

            binding.webView.loadDataWithBaseURL(
                null, htmlData, null, "utf-8", null
            )
        }
    }

    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        inflater.inflate(R.menu.article_menu, menu)
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when(item.itemId) {
            android.R.id.home -> {
                view?.findNavController()?.navigate(R.id.action_articleFragment_to_homeFragment)
            }
        }
        return super.onOptionsItemSelected(item)
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

}