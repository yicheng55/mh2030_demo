(function () {
  let zoom = 1;

  function applyZoom(img) {
    img.style.transform = `scale(${zoom})`;
  }

  document.addEventListener("DOMContentLoaded", function () {
    const modal = document.getElementById("svgModal");
    const modalTitle = document.getElementById("svgModalTitle");
    const modalImg = document.getElementById("svgModalImg");
    const zoomInBtn = document.getElementById("zoomIn");
    const zoomOutBtn = document.getElementById("zoomOut");
    const zoomResetBtn = document.getElementById("zoomReset");

    if (!modal || !modalImg) {
      return;
    }

    document.querySelectorAll(".figure-viewport img").forEach((img) => {
      img.addEventListener("click", function () {
        zoom = 1;
        modalImg.src = img.src;
        modalImg.alt = img.alt || "diagram";
        modalTitle.textContent = img.dataset.title || img.alt || "SVG Diagram";
        applyZoom(modalImg);
        if (window.bootstrap) {
          const inst = new bootstrap.Modal(modal);
          inst.show();
        }
      });
    });

    if (zoomInBtn) {
      zoomInBtn.addEventListener("click", function () {
        zoom = Math.min(5, zoom + 0.2);
        applyZoom(modalImg);
      });
    }
    if (zoomOutBtn) {
      zoomOutBtn.addEventListener("click", function () {
        zoom = Math.max(0.3, zoom - 0.2);
        applyZoom(modalImg);
      });
    }
    if (zoomResetBtn) {
      zoomResetBtn.addEventListener("click", function () {
        zoom = 1;
        applyZoom(modalImg);
      });
    }

    modalImg.addEventListener(
      "wheel",
      function (e) {
        e.preventDefault();
        zoom = e.deltaY < 0 ? Math.min(5, zoom + 0.1) : Math.max(0.3, zoom - 0.1);
        applyZoom(modalImg);
      },
      { passive: false }
    );
  });
})();
