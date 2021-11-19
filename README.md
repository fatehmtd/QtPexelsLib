# QtPexelsLib
Pexels Client made with Qt (works with Qt5 and Qt6) and C++ (11+), you will need to get an API KEY for your app here : https://www.pexels.com/api/.

**_NOTE:_**   The included Api Key will soon be disabled as it was just for demonstration purposes.

# Whats included
Both the Photos and Videos apis are supported, including :
  * querying the currated pohtos as well a custom query (search) operation
  * querying the popular videos as well a custom query (search) operation

# Usage and Examples

First of all, you need an instance of `qtpexels::ApiClient` with an `API_KEY` in order to query data from `pexels.com`.
```c++
qtpexels::ApiClient apiClient("API_KEY_GOES_HERE");
```
Once a valid api key is provided, you can query specific resourses such as `photos` and `videos`.

```c++
    ////////////
    // Photos //
    ////////////

    PhotosPage* queryCurratedPhotos(uint page = 1, uint itemsPerPage = 15) const;

    PhotosPage* queryPhotos(const QString& queryTerm, int page = 1, int itemsPerPage = 15) const;
    PhotosPage* queryPhotos(const QString& queryTerm, const PhotoQueryParams& queryParams, int page = 1, int itemsPerPage = 15) const;

    Photo* queryPhoto(int id) const;

    ////////////
    // Videos //
    ////////////

    VideosPage* queryPopularVideos(uint page = 1, uint itemsPerPage = 15) const;
    VideosPage* queryPopularVideos(const VideoPopularQueryParams& popularQueryParams, uint page = 1, uint itemsPerPage = 15) const;

    VideosPage* queryVideos(const QString& queryTerm, int page = 1, int itemsPerPage = 15) const;
    VideosPage* queryVideos(const QString& queryTerm, const VideoQueryParams& queryParams, int page = 1, int itemsPerPage = 15) const;

    Video* queryVideo(int id) const;
```

The `querySomething` methods return either a single resource such as `Photo*` or `Video*`, or a collection of results in the form of a `ResultsPage` as in `PhotosPage`  `VideosPage`. Once the instance is created you have to connect to both its signals `finished` in the case of success or `errorOccured` in the case of failure.

Once the `finished` signal is emitted, the result instance will contain the necessary data decoded from a `JSON` response from the web api.

The included example `example/main.cpp` contains several usecases

```c++
void queryCuratedPhotos(const qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryCurratedPhotos(1, 10);
    connectLogging(resultsPage, "** Query Curated Photos : ");
}

void queryPopularVideos(const qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryPopularVideos(1, 10);
    connectLogging(resultsPage, "** Query popular videos : ");
}

void queryPhotosWithParams(const qtpexels::ApiClient& client)
{
    qtpexels::PhotoQueryParams queryParams;
    //queryParams.orientation = qtpexels::Orienation::LANDSCAPE;
    queryParams.size = qtpexels::Size::LARGE;

    auto resultsPage = client.queryPhotos("space", // keyword
        queryParams, // query params, ie: size and orientation
        1, // page index starting from 1
        10); // number of items per page

    connectLogging(resultsPage, "** Query Photos with params : ");
}

void queryVideosWithParams(const qtpexels::ApiClient& client)
{
    auto resultsPage = client.queryVideos("green", 1, 10); // search videos with the "green" keyword

    connectLogging(resultsPage, "** Query Videos with params : ");
}
```
The `void connectLogging(qtpexels::ResultsPage* resultsPage, QString title)` function connects to both the `finished` and `errorOccured` signals, processing is done in both cases.

```c++
void connectLogging(qtpexels::ResultsPage* resultsPage, QString title)
{
    QObject::connect(resultsPage, &qtpexels::ResultsPage::finished, resultsPage, [=]() {
        logInfo(resultsPage, title);
        logRequestStats(resultsPage->apiClient());
    });

    QObject::connect(resultsPage, &qtpexels::ResultsPage::errorOccured, resultsPage, [=]() {
        qDebug() << "*** Error : " << title << " message : " << resultsPage->error();
        logRequestStats(resultsPage->apiClient());
    });
}
```

# TODO
  * Add support for the Collections api
