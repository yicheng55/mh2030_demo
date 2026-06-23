(function() {
  function initSVGModals() {
    document.querySelectorAll('.figure-card[data-svg]').forEach(function(card) {
      var svgPath = card.getAttribute('data-svg');
      var modalId = card.getAttribute('data-modal-id');
      var modalEl = document.getElementById(modalId);
      if (!modalEl) return;

      var figureBody = card.querySelector('.figure-body');
      if (!figureBody) return;

      figureBody.style.cursor = 'pointer';
      figureBody.title = 'Click to view full screen';

      figureBody.addEventListener('click', function() {
        var img = modalEl.querySelector('.svg-zoomable');
        if (img) img.setAttribute('src', svgPath);
        var modal = bootstrap.Modal.getOrCreateInstance(modalEl);
        modal.show();
      });
    });
  }

  function initZoomControls() {
    document.querySelectorAll('.modal').forEach(function(modalEl) {
      if (modalEl.getAttribute('data-zoom-initialized')) return;
      modalEl.setAttribute('data-zoom-initialized', '1');

      modalEl.addEventListener('shown.bs.modal', function() {
        var container = modalEl.querySelector('.svg-zoom-container');
        var img = modalEl.querySelector('.svg-zoomable');
        if (!container || !img) return;

        var scale = 1;

        function applyZoom() {
          img.style.transform = 'scale(' + scale + ')';
          container.style.overflow = scale > 1 ? 'auto' : 'hidden';
          container.style.cursor = scale > 1 ? 'grab' : 'zoom-in';
          var levelBadge = modalEl.querySelector('.svg-zoom-level');
          if (levelBadge) levelBadge.textContent = Math.round(scale * 100) + '%';
        }

        function zoomIn() {
          if (scale < 5) { scale = Math.min(scale + 0.25, 5); applyZoom(); }
        }

        function zoomOut() {
          if (scale > 0.25) { scale = Math.max(scale - 0.25, 0.25); applyZoom(); }
        }

        function zoomReset() {
          scale = 1;
          container.scrollLeft = 0;
          container.scrollTop = 0;
          applyZoom();
        }

        // Share zoom functions via dataset for buttons
        container._zoomIn = zoomIn;
        container._zoomOut = zoomOut;
        container._zoomReset = zoomReset;

        applyZoom();
      });

      // Zoom button handlers (use event delegation on modal footer)
      modalEl.querySelector('.modal-footer')?.addEventListener('click', function(e) {
        var btn = e.target.closest('.svg-zoom-btn');
        if (!btn) return;
        var container = modalEl.querySelector('.svg-zoom-container');
        if (!container) return;
        var action = btn.getAttribute('data-action');
        if (action === 'zoom-in') container._zoomIn && container._zoomIn();
        else if (action === 'zoom-out') container._zoomOut && container._zoomOut();
        else if (action === 'zoom-reset') container._zoomReset && container._zoomReset();
      });

      // Mouse wheel zoom on container (delegated via shown event)
      modalEl.addEventListener('shown.bs.modal', function() {
        var container = modalEl.querySelector('.svg-zoom-container');
        if (!container || container._wheelAttached) return;
        container._wheelAttached = true;

        container.addEventListener('wheel', function(e) {
          if (e.ctrlKey || e.metaKey) {
            e.preventDefault();
            if (e.deltaY < 0) container._zoomIn && container._zoomIn();
            else container._zoomOut && container._zoomOut();
          }
        }, { passive: false });

        container.addEventListener('dblclick', function(e) {
          e.preventDefault();
          container._zoomReset && container._zoomReset();
        });

        // Pan
        var isPanning = false, startX, startY, scrollLeft, scrollTop;
        container.addEventListener('mousedown', function(e) {
          var s = parseFloat(container.querySelector('.svg-zoomable')?.style.transform?.match(/scale\(([\d.]+)\)/)?.[1]) || 1;
          if (s > 1) {
            isPanning = true;
            this.style.cursor = 'grabbing';
            startX = e.pageX - this.offsetLeft;
            startY = e.pageY - this.offsetTop;
            scrollLeft = this.scrollLeft;
            scrollTop = this.scrollTop;
          }
        });
        container.addEventListener('mousemove', function(e) {
          if (!isPanning) return;
          e.preventDefault();
          this.scrollLeft = scrollLeft - (e.pageX - this.offsetLeft - startX) * 1.5;
          this.scrollTop = scrollTop - (e.pageY - this.offsetTop - startY) * 1.5;
        });
        container.addEventListener('mouseup', function() { isPanning = false; });
        container.addEventListener('mouseleave', function() { isPanning = false; });

        // Touch pinch zoom
        var lastDist = 0;
        container.addEventListener('touchstart', function(e) {
          if (e.touches.length === 2) {
            var dx = e.touches[0].clientX - e.touches[1].clientX;
            var dy = e.touches[0].clientY - e.touches[1].clientY;
            lastDist = Math.sqrt(dx * dx + dy * dy);
          }
        }, { passive: true });
        container.addEventListener('touchmove', function(e) {
          if (e.touches.length !== 2) return;
          e.preventDefault();
          var dx = e.touches[0].clientX - e.touches[1].clientX;
          var dy = e.touches[0].clientY - e.touches[1].clientY;
          var dist = Math.sqrt(dx * dx + dy * dy);
          if (lastDist > 0) {
            if (dist > lastDist + 5) container._zoomIn && container._zoomIn();
            else if (dist < lastDist - 5) container._zoomOut && container._zoomOut();
          }
          lastDist = dist;
        }, { passive: false });
      });

      // Reset scroll on close
      modalEl.addEventListener('hidden.bs.modal', function() {
        var container = modalEl.querySelector('.svg-zoom-container');
        if (container) { container.scrollLeft = 0; container.scrollTop = 0; }
      });
    });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', function() { initSVGModals(); initZoomControls(); });
  } else {
    initSVGModals();
    initZoomControls();
  }
})();
