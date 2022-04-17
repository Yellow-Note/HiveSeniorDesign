<template>   
  <nav class="navbar navbar-expand-lg navbar-dark bg-dark">
    <div class="container-fluid">
      <a class="navbar-brand" href="/">Hive</a>
      <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
        <span class="navbar-toggler-icon"></span>
      </button>
      <div class="collapse navbar-collapse" id="navbarSupportedContent">
        <ul class="navbar-nav me-auto mb-2 mb-lg-0">
          <li class="nav-item">
            <a class="nav-link"  href="/getting-started">Getting Started</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="/gps">GPS</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="/queue">Queue</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="/tutorial">Tutorial</a>
          </li>
        </ul>
        <button 
        type="button" 
        class="btn btn-secondary" 
        data-bs-toggle="modal" 
        data-bs-target="#exampleModal"
        @click="$emit('openSettings')"
        >
          <img src="@/assets/Icons/gear-fill.svg" alt="Settings" width="32" height="32" >
        </button>
      </div>
    </div>
  </nav>
  
</template>
<script>

</script>