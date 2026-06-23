(function() {
  function buildTOC() {
    const content = document.getElementById('mainContent');
    const sidebar = document.getElementById('sidebarNav');
    if (!content || !sidebar) return;

    const headings = content.querySelectorAll('h1, h2, h3, h4');
    const sections = [];
    let currentH1 = null, currentH2 = null, currentH3 = null;

    headings.forEach(function(h) {
      if (!h.id) {
        h.id = h.textContent.trim().toLowerCase().replace(/[^a-z0-9\u4e00-\u9fff]+/g, '-').replace(/(^-|-$)/g, '');
      }
      sections.push({ el: h, tag: h.tagName, id: h.id, text: h.textContent.trim() });
    });

    let html = '<div class="nav-section"><div class="nav-section-title">Contents</div>';
    sections.forEach(function(s) {
      if (s.tag === 'H1') {
        html += '<div class="nav-item" data-target="' + s.id + '"><span class="icon"><i class="bi bi-file-text"></i></span>' + s.text + '</div>';
        currentH1 = s;
        currentH2 = null;
        currentH3 = null;
      } else if (s.tag === 'H2') {
        html += '<div class="nav-item sub-item" data-target="' + s.id + '"><span class="icon"><i class="bi bi-dot"></i></span>' + s.text + '</div>';
        currentH2 = s;
        currentH3 = null;
      } else if (s.tag === 'H3') {
        html += '<div class="nav-item sub-sub-item" data-target="' + s.id + '"><span class="icon"><i class="bi bi-dot"></i></span>' + s.text + '</div>';
        currentH3 = s;
      }
    });
    html += '</div>';

    html += '<div class="nav-section"><div class="nav-section-title">Figures</div>';
    document.querySelectorAll('.figure-card').forEach(function(card, idx) {
      const header = card.querySelector('.figure-header');
      if (header) {
        const figId = 'figure-' + (idx + 1);
        card.id = figId;
        html += '<div class="nav-item sub-item" data-target="' + figId + '"><span class="icon"><i class="bi bi-image"></i></span>' + header.textContent.trim() + '</div>';
      }
    });
    html += '</div>';

    sidebar.innerHTML = html;

    sidebar.querySelectorAll('.nav-item[data-target]').forEach(function(item) {
      item.addEventListener('click', function(e) {
        e.preventDefault();
        const target = document.getElementById(this.getAttribute('data-target'));
        if (target) {
          const offset = 70;
          const top = target.getBoundingClientRect().top + window.pageYOffset - offset;
          window.scrollTo({ top: top, behavior: 'smooth' });

          if (window.innerWidth < 992) {
            const offcanvas = bootstrap.Offcanvas.getInstance(document.getElementById('sidebarOffcanvas'));
            if (offcanvas) offcanvas.hide();
          }
        }
      });
    });
  }

  function updateActiveNav() {
    const items = document.querySelectorAll('.sidebar .nav-item[data-target]');
    if (!items.length) return;

    let currentId = '';
    const scrollPos = window.scrollY + 80;

    document.querySelectorAll('h1[id], h2[id], h3[id], .figure-card[id]').forEach(function(el) {
      if (el.offsetTop <= scrollPos) {
        currentId = el.id;
      }
    });

    items.forEach(function(item) {
      item.classList.remove('active');
      if (item.getAttribute('data-target') === currentId) {
        item.classList.add('active');
        item.scrollIntoView({ block: 'nearest', behavior: 'smooth' });
      }
    });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', buildTOC);
  } else {
    buildTOC();
  }

  window.addEventListener('scroll', updateActiveNav, { passive: true });
})();
