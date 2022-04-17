
<template>
  <div :class="currentTheme">
      <hive-nav @openSettings="showModal = true" />
      <router-view/>
      <settings-modal/>
      <Teleport to="body">
        <!-- use the modal component, pass in the prop -->
        <settings-modal :show="showModal" @close="showModal = false">
          <template #header>
            <div>Settings</div>
          </template>
          <template #body>
            <p>
              <button class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#ThemeOptions" aria-expanded="false" aria-controls="ThemeOptions">
                Set Theme
              </button>
            </p>
            <div>
              <div class="collapse collapse-horizontal" id="ThemeOptions">
                <div class="card card-body" style="width: 300px;">
                  <div class="list-group">
                    <button type="button" class="list-group-item" @click="theme='dark-theme'">Dark Theme</button>
                    <button type="button" class="list-group-item" @click="theme='light-theme'">Light Theme</button>
                    <button type="button" class="list-group-item" @click="theme='basic-theme'">Basic Theme</button>
                    <button type="button" class="list-group-item" @click="theme='gradiant-theme'">Gradiant Theme</button>
                    <button type="button" class="list-group-item" @click="theme='repeatImage-theme'">Repeating Image Theme</button>
                  </div>
                </div>
              </div>
            </div>
                        <p>
              <button class="btn btn-primary" type="button" data-bs-toggle="collapse" data-bs-target="#collapseWidthExample" aria-expanded="false" aria-controls="collapseWidthExample">
                Toggle width collapse
              </button>
            </p>
            <div>
              <div class="collapse collapse-horizontal" id="collapseWidthExample">
                <div class="card card-body" style="width: 300px;">
                  This is some placeholder content for a horizontal collapse. It's hidden by default and shown when triggered.
                </div>
              </div>
            </div>
          </template>
          <template #footer>
            <div>
              <button
              type="button" 
              class="btn btn-secondary"
              @click="showModal = false"
              >
              Close
              </button>
            </div>
          </template>
        </settings-modal>
      </Teleport>
    </div>
</template>


<script>
import hiveNav from './components/hiveNav.vue'
import settingsModal from './components/settingsModal.vue'

export default{
  setup() {

  },

  data() {
    return {
      isModalVisible: true,
      showModal: false,
      theme: 'dark-theme',
    };
  },
  components: { 
    'hive-nav': hiveNav,
    'settings-modal': settingsModal
  },
  computed: {
    currentTheme: function () {
      return this.theme + '-background'
    }
  }
}
</script>
<style lang="scss">
@import '@/assets/scss/custom.scss';
</style>

