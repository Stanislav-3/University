#include "informationwindow.h"
#include "ui_informationwindow.h"
#include <QFormBuilder>
#include <QMessageBox>
#include <QtWidgets>
#include <QLabel>

InformationWindow::InformationWindow(QWidget *parent) :QDialog(parent), ui(new Ui::InformationWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("<Information>");
    this->setFixedSize(320, 381);
}

InformationWindow::~InformationWindow()
{
    delete ui;
}

void InformationWindow::showInformation(int windowLength, QString sortName, QString gifPath, int gifLength, QString CC, QString memory, QString stability, QString otherInformation, QString description)
{
    /* Ui load*/
    QFormBuilder loader;
    QFile file(":/myDialogs/sortInfo.ui");
    file.open(QFile::ReadOnly);
    QWidget *dialog = loader.load(&file, this);
    file.close();
    dialog->setWindowModality(Qt::WindowModal);
    dialog->setFixedSize(450, windowLength);

    /* Ui items' initialization */
    QLabel *gifLabel = findChild<QLabel*>("gifLabel");
    QLabel *CCWorstLabel = findChild<QLabel*>("CCWorstLabel");
    QLabel *CCAverageLabel = findChild<QLabel*>("CCAverageLabel");
    QLabel *CCBestLabel = findChild<QLabel*>("CCBestLabel");
    QLabel *memoryLabel = findChild<QLabel*>("MemoryLabel");
    QLabel *stabilityLabel = findChild<QLabel*>("StabilityLabel");
    QLabel *otherInformationLabel = findChild<QLabel*>("otherInformationLabel");
    QLabel *descriptionLabel = findChild<QLabel*>("descriptionLabel");
    QLabel *descriptionName = findChild<QLabel*>("label_8");
    QMovie *movie = nullptr;
    if (gifLength != 0) {
        movie = new QMovie(gifPath, QByteArray(), gifLabel);
    }
    else {
        QLabel *animationName = findChild<QLabel*>("label_9");
        animationName->close();
        gifLabel->close();
        gifLength = -16;
    }
    QPushButton *OkButton = findChild<QPushButton*>("pushButton");

    /* Setting information */
    this->setWindowTitle(sortName);
    if (movie) {
        gifLabel->setGeometry(10, 170, 431, gifLength);
        gifLabel->setMovie(movie);
        gifLabel->movie()->scaledSize();
    }
    QStringList CCList = CC.split(" ", QString::SkipEmptyParts);
    CCBestLabel->setText(CCList[0]);
    CCAverageLabel->setText(CCList[1]);
    CCWorstLabel->setText(CCList[2]);
    memoryLabel->setText(memory);
    stabilityLabel->setText(stability);
    otherInformationLabel->setGeometry(180, 70, 264, 71);
    otherInformationLabel->setText(otherInformation);
    descriptionName->move(QPoint(10, 170 + gifLength + 9));
    descriptionLabel->setGeometry(10, 195 + gifLength, 435, windowLength - (225 + gifLength));
    OkButton->move(QPoint(340, windowLength - 30));
    descriptionLabel->setText(description);
    if (movie) movie->start();
    dialog->show();

    /* Check if "OK" button is clicked */
    while(true) {
        if (OkButton->isDown()) {
            dialog->close();
            delete movie;
            delete dialog;
            this->setWindowTitle("<Information>");
            break;
        }
        QApplication::processEvents();
    }
}

void InformationWindow::on_returnButton_clicked()
{
    InformationWindow::~InformationWindow();
}

void InformationWindow::on_helpButton_clicked()
{
    QMessageBox::information(this, "<Help>", "❖Just click on any button to see the information about corresponding sorting method");
}

void InformationWindow::on_bubbleSortButton_clicked()
{
    showInformation(560, "Bubble Sort", ":/sortGifs/SortAnimations/BubbleSort.gif", 237, "n n² n²", "1", "stable",
                    "This simple algorithm performs poorly in\n"
                    "real world use and is used primarily as an\n"
                    "educational tool. More efficient algorithms\n"
                    "such as timsort, or merge sort are used.",
                    "Bubble sort, sometimes referred to as sinking sort, is a simple sorting\n"
                    "algorithm that repeatedly steps through the list, compares adjacent\n"
                    "elements and swaps them if they are in the wrong order. The pass\n"
                    "through the list is repeated until the list is sorted. The algorithm, which\n"
                    "is a comparison sort, is named for the way smaller or larger elements\n"
                    "\"bubble\" to the top of the list.");
}

void InformationWindow::on_shakerSortButton_clicked()
{
    showInformation(550, "Shaker sort", ":/sortGifs/SortAnimations/ShakerSort.gif", 255,  "n n² n²", "1", "stable",
                    "Shaker sort is an extension of bubble sort.",
                    "The algorithm extends bubble sort by operating in two directions.\n"
                    "While it improves on bubble sort by more quickly moving items to the\n"
                    "beginning of the list, it provides only marginal performance\n"
                    "improvements.");
}

void InformationWindow::on_insertionSortButton_clicked()
{
    showInformation(560, "Insertion sort", ":/sortGifs/SortAnimations/InsertionSort.gif", 180,  "n n² n²", "1", "stable",
                    "O(n + d), in the worst case over sequences\nthat have d inversions.",
                    "Insertion sort is a simple sorting algorithm that builds the final sorted\n"
                    "array(or list) one item at a time. It is much less efficient on large lists\n"
                    "than more advanced algorithms such as quicksort, heapsort, or merge\n"
                    "sort. However, insertion sort provides several advantages:\n"
                    "⋆ Simple implementation\n"
                    "⋆ Adaptive, stable, in-place, online\n"
                    "⋆ Efficient for (quite) small data sets, much like other quadratic sorting\n "
                    "  algorithms and better than most other simple quadratic algorithms \n"
                    "   e.g. selection sort or bubble sort.");
}

void InformationWindow::on_shellsortButton_clicked()
{
    showInformation(720, "Shell sort", ":/sortGifs/SortAnimations/ShellSort.gif", 344,  "n⋆logn n^(4/3) n^(3/2)", "1", "not stable",
                    "✚Small code size.",
                    "Shell sort is an in-place comparison sort. It can be seen as either a\n"
                    "generalization of sorting by exchange (bubble sort) or sorting by\n"
                    "insertion (insertion sort). The method starts by sorting pairs of\n"
                    "elements far apart from each other, then progressively reducing the gap\n"
                    "between elements to be compared. By starting with far apart elements,\n"
                    "it can move some out-of-place elements into position faster than a\n"
                    "simple nearest neighbor exchange. The running time of Shellsort is\n"
                    "heavily dependent on the gap sequence it uses. In practise, determining\n"
                    "their time complexity remains an open problem.");
}

void InformationWindow::on_selectionSortButton_clicked()
{
    showInformation(720, "Selection sort", ":/sortGifs/SortAnimations/SelectionSort.gif", 288,  "n² n² n²", "1", "not stable",
                    "Stable with O(n) extra space or when using\n"
                    "linked lists, in-place.",
                    "The algorithm divides the input list into two parts: a sorted sublist of\n"
                    "items which is built up from left to right at the front (left) of the list\n"
                    "and a sublist of the remaining unsorted items that occupy the rest of\n"
                    "the list. Initially, the sorted sublist is empty and the unsorted sublist\n"
                    "is the entire input list. The algorithm proceeds by finding the smallest\n"
                    "(or largest) element in the unsorted sublist, swapping it with the\n"
                    "leftmost unsorted element (putting it in sorted order), and moving the\n"
                    "sublist boundaries one element to the right.\n"
                    "It has an O(n2) time complexity, so there are a number of sorting\n"
                    "techniques which have better time complexity than selection sort. One\n"
                    "thing which distinguishes selection sort from others algorithms is\n"
                    "that it makes the minimum possible number of swaps, n − 1 in the worst\n"
                    "case; has performance advantages where auxiliary memory is limited.");
}

void InformationWindow::on_quickSortButton_clicked()
{
    showInformation(580, "Quick sort", ":/sortGifs/SortAnimations/QuickSort.gif", 214,  "n⋆logn n⋆logn n²", "logn", "not stable",
                    "Quicksort is usually done in-place with\n"
                    "O(log n) stack space.",
                    "Partition-exchange sort is an efficient sorting algorithm. When\n"
                    "implemented well, it can be about two or three times faster than its main\n"
                    "competitors, merge sort and heapsort. Quicksort is a divide-and-\n"
                    "conquer algorithm. It works by selecting a 'pivot' element from the array\n"
                    "and partitioning the other elements into two sub-arrays, according to\n"
                    "whether they are less than or greater than the pivot. The sub-arrays are\n"
                    "then sorted recursively. This can be done in-place, requiring small\n"
                    "additional amounts of memory to perform the sorting.");
}

void InformationWindow::on_combSortButton_clicked()
{
    showInformation(600, "Comb sort", ":/sortGifs/SortAnimations/CombSort.gif", 255,  "n⋆logn n² n²", "1", "not stable",
                    "Comb sort is a relatively simple sorting\n"
                    "algorithm.",
                    "In bubble sort, when any two elements are compared, they always have\n"
                    "a gap (distance from each other) of 1. The basic idea of comb sort is\n"
                    "that the gap can be much more than 1. The inner loop of bubble sort,\n"
                    "which does the actual swap, is modified such that the gap between\n"
                    "swapped elements goes down (for each iteration of outer loop) in steps\n"
                    "of a \"shrink factor\" k: [ n/k, n/k2, n/k3, ..., 1 ], where optimal shrink\n"
                    "factor(k) about 2.2.");
}

void InformationWindow::on_mergeSortButton_clicked()
{
    showInformation(490, "Merge sort", ":/sortGifs/SortAnimations/MergeSort.gif", 180,  "n⋆logn n⋆logn n⋆logn", "n", "stable",
                    "Mergesort is an efficient, general-purpose,\n"
                    "comparison-based sorting divide-and-\n"
                    "conquer algorithm. Mostly stable.",
                    "Conceptually, a merge sort works as follows:\n"
                    "⋆ Divide the unsorted list into n sublists, each containing one element\n"
                    "   (a list of one element is considered sorted).\n"
                    "⋆ Repeatedly merge sublists to produce new sorted sublists until there\n"
                    "   is only one sublist remaining. This will be the sorted list.");
}

void InformationWindow::on_heapsortButton_clicked()
{
    showInformation(620, "Heapsort", ":/sortGifs/SortAnimations/HeapSort.gif", 279,  "n⋆logn n⋆logn n⋆logn", "1", "not stable",
                    "Heapsort can be thought of as an improved\n"
                    "selection sort.",
                    "Like selection sort, heapsort divides its input into a sorted and an\n"
                    "unsorted region, and it iteratively shrinks the unsorted region by\n"
                    "extracting the largest element from it and inserting it into the sorted\n"
                    "region. Unlike selection sort, heapsort does not waste time with a\n"
                    "linear-time scan of the unsorted region; rather, heap sort maintains the\n"
                    "unsorted region in a heap data structure to more quickly find the\n"
                    "largest element in each step.");
}

void InformationWindow::on_gnomeSortButton_clicked()
{
    showInformation(610, "Gnome sort", ":/sortGifs/SortAnimations/GnomeSort.gif", 320,  "n n² n²", "1", "stable",
                    "✚Small code size.\n"
                    "−Also named \"stupid sort\".",
                    "The gnome sort is a sorting algorithm which is similar to insertion sort\n"
                    "in that it works with one item at a time but gets the item to the proper\n"
                    "place by a series of swaps, similar to a bubble sort. It is conceptually\n"
                    "simple, requiring no nested loops.");
}

void InformationWindow::on_timsortButton_clicked()
{
    showInformation(560, "Timsort", ":/sortGifs/SortAnimations/TimSort.gif", 233,  "n n⋆logn n⋆logn", "n", "stable",
                    "Timsort is a hybrid stable sorting algorithm,\n"
                    "derived from merge sort and insertion sort.",
                    "Timsort is a hybrid stable sorting algorithm, derived from merge sort\n"
                    "and insertion sort, designed to perform well on many kinds of real-world\n"
                    "data. It was implemented by Tim Peters in 2002 for use in the Python\n"
                    "programming language. The algorithm finds subsequences of the data\n"
                    "that are already ordered and uses them to sort the remainder more\n"
                    "efficiently. This is done by merging runs until certain criteria are fulfilled.");
}

void InformationWindow::on_bucketSortButton_clicked()
{
    showInformation(470, "Bucket sort", "", 0,  "- n+k/n+r n²⋆k/n+r", "n⋆k/n+r", "stable",
                    "←uniform/integer keys\n"
                    "If r is O(n), then average time complexity\n"
                    "is O(n).",
                    "Bucket sort, or bin sort, is a sorting algorithm that works by distributing\n"
                    "the elements of an array into a number of buckets. Each bucket is then\n"
                    "sorted individually, either using a different sorting algorithm, or by\n"
                    "recursively applying the bucket sorting algorithm. It is a distribution sort,\n"
                    "a generalization of pigeonhole sort, and is a cousin of radix sort in the\n"
                    "MSDflavor. Bucket sort can be implemented with comparisons and\n"
                    "therefore can also be considered a comparison sort algorithm. The\n"
                    "computational complexity depends on the algorithm used to sort each\n"
                    "bucket, the number of buckets to use, and whether the input is\n"
                    "uniformly distributed.\n"
                    "Bucket sort works as follows:\n"
                    "⋆ Set up an array of initially empty \"buckets\"\n"
                    "⋆ Scatter: Go over the original array, putting each object in its bucket\n"
                    "⋆ Sort each non-empty bucket.\n"
                    "⋆ Gather: Visit the buckets in order and put all elements back into the\n"
                    "   original array.");
}

void InformationWindow::on_LSDSortButton_clicked()
{
    showInformation(340, "Radix sort (Least Significant Digit)", "", 0,  "- n⋆k/d n⋆k/d", "n+2^(d)", "stable",
                    "k/d recursion levels, 2^(d) for count array.",
                    "In computer science, radix sort is a non-comparative sorting algorithm.\n"
                    "It avoids comparison by creating and distributing elements into buckets\n"
                    "according to their radix. For elements with more than one significant\n"
                    "digit, this bucketing process is repeated for each digit, while preserving\n"
                    "the ordering of the prior step, until all digits have been considered. For\n"
                    "this reason, radix sort has also been called bucket sort and digital sort.\n"
                    "Radix sort can be applied to data that can be sorted lexicographically,\n"
                    "be they integers, words, punch cards, playing cards, or the mail.");
}

void InformationWindow::on_MSDSortButton_clicked()
{
    showInformation(340, "Radix sort (Most Significant Digit)", "", 0,  "- n⋆k/d n⋆k/d", "n+2^(d)", "stable",
                    "Stable version uses an external array of\n"
                    "size n to hold all of the bins.",
                    "In computer science, radix sort is a non-comparative sorting algorithm.\n"
                    "It avoids comparison by creating and distributing elements into buckets\n"
                    "according to their radix. For elements with more than one significant\n"
                    "digit, this bucketing process is repeated for each digit, while preserving\n"
                    "the ordering of the prior step, until all digits have been considered. For\n"
                    "this reason, radix sort has also been called bucket sort and digital sort.\n"
                    "Radix sort can be applied to data that can be sorted lexicographically,\n"
                    "be they integers, words, punch cards, playing cards, or the mail.");
}

void InformationWindow::on_treeSortButton_clicked()
{
    showInformation(310, "Tree sort", "", 0,  "n⋆logn n⋆logn n⋆logn", "n", "stable",
                    "When using a self-balancing binary\n"
                    "search tree.",
                    "Making tree sorting, thus it's a 'fast sort' process, being degree-optimal\n"
                    "for a comparison sort. However, tree sort algorithms require separate\n"
                    "memory to be allocated for the tree, as opposed to in-place algorithms\n"
                    "such as quicksort or heapsort. On most common platforms, this means\n"
                    "that heap memory has to be used, which is a significant performance\n"
                    "hit when compared to quicksort and heapsort.");
}

void InformationWindow::on_bitonicSortButton_clicked()
{
    showInformation(390, "Bitonic sort", "", 0,  "(logn)^2 (logn)^2 (logn)^2", "n(logn)^2", "not stable",
                    "",
                    "Bitonic sort is a comparison-based sorting algorithm that can be run in\n"
                    "parallel. It focuses on converting a random sequence of numbers into a\n"
                    "bitonic sequence, one that monotonically increases, then decreases.\n"
                    "Rotations of a bitonic sequence are also bitonic. More specifically,\n"
                    "bitonic sort can be modelled as a type of sorting network. The initial\n"
                    "unsorted sequence enters through input pipes, where a series of\n"
                    "comparators switch two entries to be in either increasing or decreasing\n"
                    "order.The algorithm, created by Ken Batcher in 1968, consists of two\n"
                    "parts. First, the unsorted sequence is built into a bitonic sequence;\n"
                    "then, the series is split multiple times into smaller sequences until\n"
                    "the input is in sorted order.");
}

void InformationWindow::on_moreButton_clicked()
{
    QMessageBox::information(this, "<More>", "More sort algorithms and information you can find in the web via the internet ⇪");
}
