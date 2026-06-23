(function() {
  function initSVGModals() {
    document.querySelectorAll('.figure-card[data-svg]').forEach(function(card) {
      var svgPath = card.getAttribute('data-svg');
      var modalId = card.getAttribute('data-modal-id');
      var modalEl = document.getElementById(modalId);
      if (!modalEl) return;

      card.querySelector('.figure-body').addEventListener('click', function() {
        var modalBody = modalEl.querySelector('.modal-body');
        if (modalBody) {
          modalBody.innerHTML = '<object data="' + svgPath + '" type="image/svg+xml" style="max-width:100%;height:auto;">SVG</object>';
        }
        var modal = new bootstrap.Modal(modalEl);
        modal.show();
      });

      modalEl.addEventListener('hidden.bs.modal', function() {
        var modalBody = modalEl.querySelector('.modal-body');
        if (modalBody) {
          modalBody.innerHTML = '';
        }
      });
    });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initSVGModals);
  } else {
    initSVGModals();
  }
})();
