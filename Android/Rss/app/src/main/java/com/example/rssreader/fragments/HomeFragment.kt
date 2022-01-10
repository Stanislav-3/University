package com.example.rssreader.fragments

import android.app.AlertDialog
import android.os.Bundle
import android.view.*
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.StaggeredGridLayoutManager
import com.example.rssreader.MainActivity
import com.example.rssreader.R
import com.example.rssreader.adapters.ArticlePreviewAdapter
import com.example.rssreader.databinding.FragmentHomeBinding
import com.example.rssreader.viewmodels.ArticleViewModel

class HomeFragment : Fragment(R.layout.fragment_home) {

    private var _binding: FragmentHomeBinding? = null
    private val binding get() = _binding!!
    private lateinit var articlePreviewAdapter: ArticlePreviewAdapter
    private lateinit var articleViewModel: ArticleViewModel
    private var baseUrl: String = ""

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setHasOptionsMenu(true)
        (activity as MainActivity).supportActionBar?.setDisplayHomeAsUpEnabled(false)
        (activity as MainActivity).supportActionBar?.setDisplayShowHomeEnabled(false)
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        _binding = FragmentHomeBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onCreateOptionsMenu(menu: Menu, inflater: MenuInflater) {
        super.onCreateOptionsMenu(menu, inflater)
        menu.clear()
        inflater.inflate(R.menu.home_menu, menu)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)
        articleViewModel = ViewModelProvider(requireActivity()).get(ArticleViewModel::class.java)
        setUpRecyclerView()
    }

    private fun setUpRecyclerView() {
        articlePreviewAdapter = ArticlePreviewAdapter()

        binding.recyclerView.apply {
            layoutManager = StaggeredGridLayoutManager(
                1,
                StaggeredGridLayoutManager.VERTICAL
            )
            setHasFixedSize(true)
            adapter = articlePreviewAdapter
        }

        activity?.let {
            articleViewModel.articles.observe(viewLifecycleOwner, { list ->
                articlePreviewAdapter.articles = list.toMutableList()
                articlePreviewAdapter.notifyDataSetChanged()
                binding.recyclerView.visibility = View.VISIBLE
                binding.progressBar.visibility = View.GONE
            })
        }
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when(item.itemId) {
            R.id.rss_url -> {
                getRSSFeedUrl()
            }
        }
        return super.onOptionsItemSelected(item)
    }

    private fun getRSSFeedUrl() {
        val input = EditText(activity)
        AlertDialog.Builder(activity).apply {
            setTitle("Enter RSS Feed URL:")
            setView(input)
            setPositiveButton("Ok") { _,_ ->
                binding.recyclerView.visibility = View.GONE
                binding.progressBar.visibility = View.VISIBLE
                baseUrl = input.text.toString().trim()
                articleViewModel.setUrl(baseUrl)
            }
            setNegativeButton("Cancel", null)
        }.show()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    override fun onResume() {
        super.onResume()
        (activity as MainActivity).supportActionBar?.setDisplayHomeAsUpEnabled(false)
        (activity as MainActivity).supportActionBar?.setDisplayShowHomeEnabled(false)
    }

}