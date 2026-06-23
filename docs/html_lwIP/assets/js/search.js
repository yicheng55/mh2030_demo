(function() {
  var searchData = [];

  function buildSearchIndex() {
    searchData = [];
    var mainContent = document.getElementById('mainContent');
    if (!mainContent) return;

    mainContent.querySelectorAll('h1, h2, h3, h4, p, li, td, th, .figure-header, code').forEach(function(el) {
      var text = el.textContent.trim();
      if (text.length < 3) return;
      var tag = el.tagName.toLowerCase();
      var type = 'content';
      var title = '';

      if (tag.match(/^h[1-4]$/)) {
        type = 'heading';
        title = text;
      } else if (el.classList.contains('figure-header')) {
        type = 'figure';
        title = text;
      } else if (tag === 'code') {
        type = 'api';
        title = text;
      } else if (tag === 'th') {
        type = 'table';
        title = 'Table: ' + text;
      }

      if (type === 'heading' || type === 'figure' || type === 'api') {
        searchData.push({ type: type, title: title, text: text, element: el });
      } else {
        var parentHeading = el.closest('h1, h2, h3, h4');
        var context = parentHeading ? parentHeading.textContent.trim() : '';
        searchData.push({ type: type, title: context || text.substring(0, 60), text: text.substring(0, 200), element: el });
      }
    });
  }

  function performSearch(query) {
    if (!query || query.length < 2) {
      document.getElementById('searchResults').classList.remove('show');
      return;
    }

    var q = query.toLowerCase();
    var results = [];

    for (var i = 0; i < searchData.length; i++) {
      var item = searchData[i];
      var idx = item.text.toLowerCase().indexOf(q);
      if (idx >= 0 || item.title.toLowerCase().indexOf(q) >= 0) {
        var preview = item.text.substring(Math.max(0, idx - 30), idx + q.length + 60);
        if (preview.length < item.text.length) preview += '...';
        results.push({
          type: item.type,
          title: item.title,
          preview: preview,
          element: item.element
        });
        if (results.length >= 50) break;
      }
    }

    var resultsDiv = document.getElementById('searchResults');
    if (!results.length) {
      resultsDiv.innerHTML = '<div class="search-result-item"><div class="result-title">No results found</div><div class="result-preview">Try different keywords</div></div>';
    } else {
      var html = '';
      var typeLabels = { heading: 'Section', figure: 'Figure', api: 'API', table: 'Table', content: 'Content' };
      for (var j = 0; j < results.length; j++) {
        var r = results[j];
        var icon = { heading: '📄', figure: '🖼', api: '🔧', table: '📊', content: '📝' }[r.type] || '📝';
        html += '<div class="search-result-item" data-idx="' + j + '">';
        html += '<div class="result-title">' + icon + ' ' + escapeHtml(r.title.substring(0, 80)) + '</div>';
        html += '<div class="result-preview">' + escapeHtml(r.preview.substring(0, 120)) + '</div></div>';
      }
      resultsDiv.innerHTML = html;

      resultsDiv.querySelectorAll('.search-result-item').forEach(function(el, idx) {
        el.addEventListener('click', function() {
          var result = results[parseInt(this.getAttribute('data-idx'))];
          if (result && result.element) {
            var target = result.element.closest('[id]') || result.element;
            if (!target.id) {
              target = result.element.closest('h1,h2,h3,h4,.figure-card');
            }
            if (target) {
              var offset = 80;
              var top = target.getBoundingClientRect().top + window.pageYOffset - offset;
              window.scrollTo({ top: top, behavior: 'smooth' });
            }
          }
          document.getElementById('searchResults').classList.remove('show');
        });
      });
    }

    resultsDiv.classList.add('show');
  }

  function escapeHtml(str) {
    var div = document.createElement('div');
    div.textContent = str;
    return div.innerHTML;
  }

  document.addEventListener('DOMContentLoaded', function() {
    buildSearchIndex();

    var searchInput = document.getElementById('searchInput');
    var searchResults = document.getElementById('searchResults');

    if (!searchInput) return;

    var debounceTimer;
    searchInput.addEventListener('input', function() {
      clearTimeout(debounceTimer);
      debounceTimer = setTimeout(function() {
        performSearch(searchInput.value.trim());
      }, 200);
    });

    searchInput.addEventListener('focus', function() {
      if (this.value.trim().length >= 2) {
        performSearch(this.value.trim());
      }
    });

    document.addEventListener('click', function(e) {
      if (!e.target.closest('.search-wrapper')) {
        searchResults.classList.remove('show');
      }
    });
  });
})();
