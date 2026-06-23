(function () {
  function clearHit() {
    document.querySelectorAll(".search-hit").forEach((el) => el.classList.remove("search-hit"));
  }

  function createSnippet(text, keyword) {
    const idx = text.toLowerCase().indexOf(keyword.toLowerCase());
    if (idx < 0) return text.slice(0, 80);
    const start = Math.max(0, idx - 24);
    const end = Math.min(text.length, idx + keyword.length + 48);
    return text.slice(start, end).replace(/\s+/g, " ");
  }

  document.addEventListener("DOMContentLoaded", function () {
    const input = document.getElementById("docSearch");
    const list = document.getElementById("searchResults");
    if (!input || !list) return;

    const nodes = Array.from(document.querySelectorAll("#doc-content h1, #doc-content h2, #doc-content h3, #doc-content h4, #doc-content p, #doc-content li, #doc-content td, #doc-content .fig-caption"));

    input.addEventListener("input", function () {
      const keyword = input.value.trim();
      clearHit();
      list.innerHTML = "";

      if (!keyword) return;

      const hits = [];
      nodes.forEach((node) => {
        const text = node.textContent || "";
        if (text.toLowerCase().includes(keyword.toLowerCase())) {
          hits.push({ node, text });
        }
      });

      hits.slice(0, 20).forEach((hit, idx) => {
        hit.node.classList.add("search-hit");
        const item = document.createElement("a");
        item.href = "#";
        item.className = "list-group-item list-group-item-action";
        item.innerHTML = `<strong>${idx + 1}.</strong> ${createSnippet(hit.text, keyword)}`;
        item.addEventListener("click", function (e) {
          e.preventDefault();
          hit.node.scrollIntoView({ behavior: "smooth", block: "center" });
        });
        list.appendChild(item);
      });
    });
  });
})();
